#include <cassert>
#include <iostream>

namespace pyro
{
	template <typename ID, typename Res>
	void ResourceHolder<ID, Res>::insertResource(ID id, const Res& res)
	{
		auto inserted = mResourceMap.insert(std::make_pair(id, std::move(res)));
		assert(inserted.second);
	}

	template <typename ID, typename Res>
	void ResourceHolder<ID, Res>::load(ID id, const std::string& filename)
	{
		Res resource;
		try {
			if (!resource.loadFromFile(filename))
				throw std::runtime_error("ResourceHolder::load - Couldn't load " + filename);
		}
		catch (std::runtime_error& e) {
			std::cout << "\nEXCEPTION: " << e.what() << std::endl;
			return;
		}

		insertResource(id, std::move(resource));
	}

	template <typename ID, typename Res>
	const Res& ResourceHolder<ID, Res>::get(ID id) const
	{
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());

		return found->second;
	}
}